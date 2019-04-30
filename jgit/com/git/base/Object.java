package com.git.base;

import java.util.Formatter;

abstract public class Object {
    private byte[] sha1;

    abstract public String getType();

    abstract public byte[] getData();

    public void setId(final byte[] sha1) {
        this.sha1 = sha1;
    }

    public byte[] getId() {
        return sha1;
    }

    public String getHex() {
        Formatter formatter = new Formatter();
        for (byte b : sha1) {
            formatter.format("%02x", b);
        }
        return formatter.toString();
    }
}
