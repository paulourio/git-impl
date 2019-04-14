"""Git command line interface."""
# pylint: disable=C0103
import os
import sys
import pathlib


command = sys.argv[1]

if command == 'init':
    path = os.path.abspath(sys.argv[2])
    root_path = pathlib.Path(path)
    git_path = root_path.joinpath('.git')

    for dirname in ['objects', 'refs']:
        try:
            git_path.joinpath(dirname).mkdir(parents=True, exist_ok=False)
        except FileExistsError as err:
            print(f'Fatal: {err}', file=sys.stderr)
            sys.exit(1)

    print(f'Initialized empty git repository in {git_path}')
else:
    print(f'git: {command!r} is not a git command.', file=sys.stderr)
    sys.exit(1)
