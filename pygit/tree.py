from binascii import unhexlify
from operator import attrgetter


class Tree:

    MODE = '100644'

    def __init__(self, entries):
        self.entries = entries

    @property
    def type(self):
        return 'tree'

    @property
    def content(self):
        entries = [
            f'{self.MODE} {entry.name}\0'.encode() + unhexlify(entry.oid)
            for entry in sorted(self.entries, key=attrgetter('name'))
        ]
        return b''.join(entries)
