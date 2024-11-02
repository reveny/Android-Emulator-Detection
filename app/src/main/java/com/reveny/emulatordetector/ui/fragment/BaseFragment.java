package com.reveny.emulatordetector.ui.fragment;

import android.os.Build;
import android.view.View;

import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;

public class BaseFragment extends Fragment {
    public void setupToolbar(Toolbar toolbar, View tipsView, int title, int menu) {
        setupToolbar(toolbar, tipsView, getString(title), menu, null);
    }

    public void setupToolbar(Toolbar toolbar, View tipsView, String title, int menu, View.OnClickListener navigationOnClickListener) {
        toolbar.setTitle(title);

        if (android.os.Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            toolbar.setTooltipText(title);
            if (tipsView != null) tipsView.setTooltipText(title);
        }
        if (menu != -1) {
            toolbar.inflateMenu(menu);
            toolbar.setOnMenuItemClickListener(this::onOptionsItemSelected);
            onPrepareOptionsMenu(toolbar.getMenu());
        }
    }

}
