package com.git;

import com.git.base.Object;

class Blob extends Object {
    private byte[] data;

    Blob(byte[] data) {
        this.data = data;
    }

    public String getType() {
        return "blob";
    }

    public byte[] getData() {
        return data;
    }
}
