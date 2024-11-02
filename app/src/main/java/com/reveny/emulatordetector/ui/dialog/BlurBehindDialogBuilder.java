package com.reveny.emulatordetector.ui.dialog;

import android.animation.ValueAnimator;
import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Build;
import android.view.SurfaceControl;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.DecelerateInterpolator;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;

import java.lang.reflect.Method;

public class BlurBehindDialogBuilder extends MaterialAlertDialogBuilder {
    private static final boolean supportBlur = getSystemProperty("ro.surface_flinger.supports_background_blur", false) && !getSystemProperty("persist.sys.sf.disable_blurs", false);

    public BlurBehindDialogBuilder(@NonNull Context context) {
        super(context);
    }

    @NonNull
    @Override
    public AlertDialog create() {
        AlertDialog dialog = super.create();
        dialog.setOnShowListener(d -> setBackgroundBlurRadius(dialog));
        return dialog;
    }

    private void setBackgroundBlurRadius(AlertDialog dialog) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            Window window = dialog.getWindow();
            if (Build.VERSION.SDK_INT >= 31) {
                assert window != null;
                window.addFlags(WindowManager.LayoutParams.FLAG_BLUR_BEHIND);
                window.getAttributes().setBlurBehindRadius(53); //android.R.styleable.Window_windowBlurBehindRadius
                window.addFlags(WindowManager.LayoutParams.FLAG_DIM_BEHIND);
            } else if (supportBlur) {
                assert window != null;
                View view = window.getDecorView();
                ValueAnimator animator = ValueAnimator.ofInt(1, 153);
                animator.setInterpolator(new DecelerateInterpolator());
                try {
                    Object viewRootImpl = view.getClass().getMethod("getViewRootImpl").invoke(view);
                    if (viewRootImpl == null) {
                        return;
                    }
                    SurfaceControl surfaceControl = (SurfaceControl) viewRootImpl.getClass().getMethod("getSurfaceControl").invoke(viewRootImpl);

                    @SuppressLint("BlockedPrivateApi") Method setBackgroundBlurRadius = SurfaceControl.Transaction.class.getDeclaredMethod("setBackgroundBlurRadius", SurfaceControl.class, int.class);
                    animator.addUpdateListener(animation -> {
                        try {
                            SurfaceControl.Transaction transaction = new SurfaceControl.Transaction();
                            setBackgroundBlurRadius.invoke(transaction, surfaceControl, animation.getAnimatedValue());
                            transaction.apply();
                        } catch (Throwable ignored) {

                        }
                    });
                } catch (Throwable ignored) {

                }
                view.addOnAttachStateChangeListener(new View.OnAttachStateChangeListener() {
                    @Override
                    public void onViewAttachedToWindow(@NonNull View v) {
                    }

                    @Override
                    public void onViewDetachedFromWindow(@NonNull View v) {
                        animator.cancel();
                    }
                });
                animator.start();
            }
        }
    }

    public static boolean getSystemProperty(String key, boolean defaultValue) {
        boolean value = defaultValue;
        try {
            @SuppressLint("PrivateApi") Class<?> c = Class.forName("android.os.SystemProperties");
            Method get = c.getMethod("getBoolean", String.class, boolean.class);
            value = (boolean) get.invoke(c, key, defaultValue);
        } catch (Exception ignored) {

        }
        return value;
    }
}
