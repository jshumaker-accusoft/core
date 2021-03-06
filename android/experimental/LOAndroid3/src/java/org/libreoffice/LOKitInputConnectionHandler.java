package org.libreoffice;

import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputConnection;

import org.mozilla.gecko.gfx.InputConnectionHandler;

public class LOKitInputConnectionHandler implements InputConnectionHandler {
    private static String LOGTAG = LOKitInputConnectionHandler.class.getSimpleName();

    @Override
    public InputConnection onCreateInputConnection(EditorInfo outAttrs) {
        return null;
    }

    @Override
    public boolean onKeyPreIme(int keyCode, KeyEvent event) {
        LOKitShell.sendKeyEvent(event);
        return false;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        LOKitShell.sendKeyEvent(event);
        return false;
    }

    @Override
    public boolean onKeyLongPress(int keyCode, KeyEvent event) {
        return false;
    }

    @Override
    public boolean onKeyMultiple(int keyCode, int repeatCount, KeyEvent event) {
        LOKitShell.sendKeyEvent(event);
        return false;
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        LOKitShell.sendKeyEvent(event);
        return false;
    }
}
