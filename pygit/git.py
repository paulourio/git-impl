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
        except Exception as err:
            print(f'Fatal: {err}', file=sys.stderr)
            sys.exit(1)

    print(f'Initialized empty git repository in {git_path}')
elif command == 'commit':
    from blob import Blob
    from database import Database
    from workspace import Workspace
    root_path = os.getcwd()
    db_path = os.path.join(root_path, '.git', 'objects')

    workspace = Workspace(os.getcwd())
    database = Database(db_path)
    for name in workspace.list_files():
        data = workspace.read_file(name)
        blob = Blob(data)
        database.store(blob)
else:
    print(f'git: {command!r} is not a git command.', file=sys.stderr)
    sys.exit(1)
