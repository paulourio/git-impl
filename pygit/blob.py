import os


class Blob:

    def __init__(self, data):
        self.data = data
        self._oid = None

    @property
    def type(self):
        return 'blob'

    @property
    def oid(self):
        return self._oid

    @oid.setter
    def oid(self, value):
        self._oid = value
