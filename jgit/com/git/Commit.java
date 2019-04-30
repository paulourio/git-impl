package com.git;

import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

import com.git.base.Object;
import com.git.Author;

class Commit extends Object {
    private String tree;
    private Author author;
    private String message;

    Commit(String tree, Author author, String message) {
        this.tree = tree;
        this.author = author;
        this.message = message;
    }

    public String getType() {
        return "commit";
    }

    public byte[] getData() {
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        try {
            stream.write("tree ".getBytes());
            stream.write(tree.getBytes());
            stream.write("\n".getBytes());
            stream.write("author ".getBytes());
            stream.write(author.toString().getBytes());
            stream.write("\n".getBytes());
            stream.write("committer ".getBytes());
            stream.write(author.toString().getBytes());
            stream.write("\n".getBytes());
            stream.write("\n".getBytes());
            stream.write(message.getBytes());
            stream.write("\n".getBytes());
        } catch (IOException err) {
            System.err.println(err);
            System.exit(1);
        }
        return stream.toByteArray();
    }
}
