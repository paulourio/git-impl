package com.git;

import java.io.File;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.nio.file.Path;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.zip.Deflater;

import com.git.base.Object;

class Database {
    private String pathname;

    Database(String pathname) {
        this.pathname = pathname;
    }

    public void store(Object obj) {
        byte[] data = obj.getData();
        String header = String.format("%s %d", obj.getType(), data.length);

        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        stream.write(header.getBytes(), 0, header.length());
        stream.write(0);
        stream.write(data, 0, data.length);

        byte[] content = stream.toByteArray();

        try {
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] sha1 = md.digest(content);

            obj.setId(sha1);

            writeObject(obj.getHex(), content);
        } catch (NoSuchAlgorithmException err) {
            System.err.println(err);
            System.exit(1);
        }
    }

    private void writeObject(String oid, byte[] content) {
        String path = String.format(".git/objects/%s/%s",
                                    oid.substring(0, 2),
                                    oid.substring(2));

        byte[] compressed = new byte[content.length];
        Deflater compresser = new Deflater();
        compresser.setInput(content);
        compresser.finish();
        int compressedDataLength = compresser.deflate(compressed);
        compresser.end();

        try {
            File tmp = File.createTempFile("obj_", null,
                                           new File(".git/objects/"));
            FileOutputStream stream = new FileOutputStream(tmp.toString());
            stream.write(compressed, 0, compressedDataLength);
            stream.close();
            File ofile = new File(path);
            File dir = ofile.getParentFile();
            if (!dir.isDirectory())
                dir.mkdirs();
            tmp.renameTo(ofile);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
