import os
import zlib
from hashlib import sha1
from tempfile import NamedTemporaryFile


class Database:

    def __init__(self, pathname):
        self.pathname = pathname

    def store(self, obj):
        header = f'{obj.type} {len(obj.data)}\0'.encode()
        content = header + obj.data
        obj.oid = sha1(content).hexdigest()
        self.write_object(obj.oid, content)

    def write_object(self, oid, content):
        object_path = os.path.join(self.pathname, oid[:2], oid[2:])
        dirname = os.path.dirname(object_path)

        if not os.path.exists(dirname):
            os.mkdir(dirname)

        tmp = NamedTemporaryFile(dir=dirname, delete=False)
        try:
            compressed = zlib.compress(content)
            tmp.write(compressed)
            tmp.close()
            os.rename(tmp.name, object_path)
        finally:
            if os.path.exists(tmp.name):
                os.delete(tmp.name)
