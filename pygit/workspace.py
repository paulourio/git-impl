import os


class Workspace:

    def __init__(self, pathname):
        self.pathname = pathname

    def list_files(self):
        return [name for name in os.listdir() if name.endswith('.py')]

    def read_file(self, path):
        path = os.path.join(self.pathname, path)
        return open(path, 'rb').read()
