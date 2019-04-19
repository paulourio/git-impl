"""Git command line interface."""
# pylint: disable=C0103
import os
import pathlib
import sys


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
    from time import time

    from author import Author
    from blob import Blob
    from commit import Commit
    from database import Database
    from entry import Entry
    from tree import Tree
    from workspace import Workspace

    root_path = os.getcwd()
    git_path = os.path.join(root_path, '.git')
    db_path = os.path.join(git_path, 'objects')

    workspace = Workspace(os.getcwd())
    database = Database(db_path)

    entries = list()
    for name in workspace.list_files():
        data = workspace.read_file(name)
        blob = Blob(data)
        database.store(blob)
        entries.append(Entry(name, blob.oid))

    tree = Tree(entries)
    database.store(tree)

    name    = os.environ['GIT_AUTHOR_NAME']
    email   = os.environ['GIT_AUTHOR_EMAIL']
    author  = Author(name, email, time())
    message = sys.stdin.read()

    commit = Commit(tree.oid, author, message)
    database.store(commit)

    with open(os.path.join(git_path, 'HEAD'), 'w+') as file:
        file.write(commit.oid)

    print(f'[(root-commit) {commit.oid}] {message.splitlines()[0]}')
    sys.exit(0)
else:
    print(f'git: {command!r} is not a git command.', file=sys.stderr)
    sys.exit(1)
