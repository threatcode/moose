#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html
import os
# import logging
import datetime
import mooseutils
import MooseDocs
from ..base import components
from ..common import exceptions
from ..tree import tokens, html
from . import command, core

def make_extension(**kwargs):
    return GitUtilsExtension(**kwargs)

class GitUtilsExtension(command.CommandExtension):
    """
    Adds ability to include git repository information.
    """

    @staticmethod
    def defaultConfig():
        config = command.CommandExtension.defaultConfig()
        return config

    def extend(self, reader, renderer):
        self.requires(core, command)
        self.addCommand(reader, CommitCommand())
        self.addCommand(reader, SubmoduleHashCommand())

class CommitCommand(command.CommandComponent):
    COMMAND = 'git'
    SUBCOMMAND = 'commit'

    @staticmethod
    def defaultSettings():
        settings = command.CommandComponent.defaultSettings()
        return settings

    def createToken(self, parent, info, page):
        content = info['inline'] if 'inline' in info else info['block']
        if content:
            raise exceptions.MooseDocsException("Content is not supported for the 'git commit' command.")

        if not mooseutils.is_git_repo():
            raise exceptions.MooseDocsException("The current working directory is not a git repository.")

        core.Word(parent, content=mooseutils.git_commit())
        return parent

class SubmoduleHashCommand(command.CommandComponent):
    COMMAND = 'git'
    SUBCOMMAND = 'submodule-hash'

    @staticmethod
    def defaultSettings():
        settings = command.CommandComponent.defaultSettings()
        settings['url'] = (None, "If provided, prefix the hash with the url to create a link.")
        return settings

    def createToken(self, parent, info, page):
        inline = 'inline' in info
        if not inline:
            raise exceptions.MooseDocsException("The '!git submodule-hash' command is an inline level command, use '[!git!submodule-hash](name)' instead.")

        name = info['inline']
        status = mooseutils.git_submodule_info(MooseDocs.ROOT_DIR, '--recursive')
        # if (name == 'moose') and any([repo.endswith('moose') for repo in status.keys()]) and (status['moose'][0] == '-'):
        #     logging.getLogger(__name__).warning("The 'moose' submodule exists but has not been initialized.")

        for repo, ginfo in status.items():
            if repo.endswith(name):
                url = self.settings['url']
                if url is None:
                    core.Word(parent, content=ginfo[1])
                else:
                    core.Link(parent, url=f"{url.rstrip('/')}/{ginfo[1]}", string=ginfo[1])
                return parent

        msg = "The submodule '{}' was not located, the available submodules are: {}"
        raise exceptions.MooseDocsException(msg, name, ', '.join(status.keys()))
