package com.git;

class Entry {
    private String path;
    private byte[] oid;

    Entry(String path, byte[] oid) {
        this.path = path;
        this.oid = oid;
    }

    public String getPath() {
        return path;
    }

    public byte[] getId() {
        return oid;
    }
}
