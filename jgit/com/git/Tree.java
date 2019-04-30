package com.git;

import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;

import com.git.base.Object;

class Tree extends Object {
    private ArrayList<Entry> entries;

    Tree() {
        entries = new ArrayList<Entry>();
    }

    void addEntry(Entry entry) {
        entries.add(entry);
    }

    public String getType() {
        return "tree";
    }

    public byte[] getData() {
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        try {
            for (Entry entry: entries) {
                stream.write("100644 ".getBytes());
                stream.write(entry.getPath().getBytes());
                stream.write(0);
                stream.write(entry.getId());
            }
        } catch (IOException err) {
            System.err.println(err);
            System.exit(1);
        }
        return stream.toByteArray();
    }
}
