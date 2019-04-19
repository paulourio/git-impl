
class Blob:

    def __init__(self, data):
        self.data = data
        self._oid = None

    @property
    def type(self):
        return 'blob'

    @property
    def content(self):
        return self.data
