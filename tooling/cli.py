"""
Command line interface code goes here
"""

# standard lib
import argparse

# local package
from tooling import settings


class Cli:
    """
    @description Wraps the built-in argparse library
    """

    def __init__(self):
        parser = argparse.ArgumentParser(
            prog="devkit",
            usage="%(prog)s [options]",
            description="A development tool for common cmake/C++ development tasks",
            allow_abbrev=False,
        )

        # create subcommand parser
        sub_commands = parser.add_subparsers(
            dest='command', help="Available subcommands")

        # create the clang tooling commands
        clang_commands = sub_commands.add_parser(
            "clang", help="Execute linting and static analyzing with clang tooling")
        clang_commands.add_argument(
            "-f",
            "--format", action="store_true", help="Format all projects recursively")
        clang_commands.add_argument(
            "-l",
            "--lint", action="store_true", help="Lints all files")

        # create the packager commands
        packager_commands = sub_commands.add_parser(
            "package", help="Build a debian, slackware, or rpm package for C/C++ software that uses the CMake build system")

        packager_commands.add_argument("-n",
                                       "--name",
                                       type=str,
                                       required=True,
                                       help="The name of the software you are packaging"
                                       )

        packager_commands.add_argument(
            "-v",
            "--version",
            type=str,
            required=True,
            help="The current version of the software you are packaging",
        )

        packager_commands.add_argument(
            "-t",
            "--type",
            type=str,
            default="debian",
            help="Choose the packaging system. Can be on of 'slackware', 'debian, or 'rpm', defaults to debian"
        )

        packager_commands.add_argument(
            "-b",
            "--build-dir",
            type=str,
            default=f"{settings.PROJECT_BUILD_DIR}",
            help="path to the build directory of your CMake build, defaults to the current working directories build folder"
        )

        # set up compiler commands
        compiler_commands = sub_commands.add_parser(
            "compile", help="Compile the entire project with clang or gcc, defaults to clang")

        compiler_commands.add_argument(
            "--clang", action="store_true", help="compile with the clang compiler", default=True)

        compiler_commands.add_argument(
            "--gnu", action="store_true", help="compile with the gnu compiler")


        # parse all the arguments
        self.__args = parser.parse_args()

    @property
    def subcommand_package(self) -> bool:
        """
        @description Return true if the package command was used
        """
        return str(self.__args.command) == "package"

    @property
    def subcommand_clang(self) -> bool:
        """
        @description Return true if the clang command was used
        """
        return str(self.__args.command) == "clang"

    @property
    def subcommand_compile(self) -> bool:
        """
        @description Return true if the compile command was used
        """
        return str(self.__args.command) == "compile"

    @property
    def args(self) -> argparse.Namespace:
        """
        @description: Return the argparse object
        """
        return self.__args
