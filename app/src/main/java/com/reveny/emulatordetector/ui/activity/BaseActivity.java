package com.reveny.emulatordetector.ui.activity;

import android.app.ActivityManager;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.view.Window;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;


import rikka.material.app.MaterialActivity;

public class BaseActivity extends MaterialActivity {

    private static Bitmap icon = null;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }
    @Override
    protected void onStart() {
        super.onStart();
        for (var task : getSystemService(ActivityManager.class).getAppTasks()) {
            task.setExcludeFromRecents(false);
        }
        if (icon == null) {
            var drawable = getApplicationInfo().loadIcon(getPackageManager());
            if (drawable instanceof BitmapDrawable) {
                icon = ((BitmapDrawable) drawable).getBitmap();
            } else {
                icon = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
                final Canvas canvas = new Canvas(icon);
                drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
                drawable.draw(canvas);
            }
        }
        setTaskDescription(new ActivityManager.TaskDescription(getTitle().toString(), icon));
    }
    @Override
    public void onApplyUserThemeResource(@NonNull Resources.Theme theme, boolean isDecorView) {
    }

    @Override
    public void onApplyTranslucentSystemBars() {
        super.onApplyTranslucentSystemBars();
        Window window = getWindow();
        window.setStatusBarColor(Color.TRANSPARENT);
        window.setNavigationBarColor(Color.TRANSPARENT);
    }
}