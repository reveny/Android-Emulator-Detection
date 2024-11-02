package com.reveny.emulatordetector.ui.fragment;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.os.Bundle;
import android.text.method.LinkMovementMethod;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.core.text.HtmlCompat;
import androidx.fragment.app.DialogFragment;

import com.reveny.emulatordetection.BuildConfig;
import com.reveny.emulatordetection.R;
import com.reveny.emulatordetection.databinding.DialogAboutBinding;
import com.reveny.emulatordetection.databinding.FragmentHomeBinding;
import com.reveny.emulatordetector.ui.dialog.BlurBehindDialogBuilder;
import com.reveny.emulatordetector.util.chrome.LinkTransformationMethod;

import rikka.material.app.LocaleDelegate;
import com.reveny.emulatordetector.plugin.EmulatorDetection;

public class HomeFragment extends BaseFragment {
    private FragmentHomeBinding binding;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onPrepareOptionsMenu(Menu menu) {
        menu.findItem(R.id.about).setOnMenuItemClickListener(item -> {
            showAbout();
            return true;
        });
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        binding = FragmentHomeBinding.inflate(inflater, container, false);
        setupToolbar(binding.toolbar, null, R.string.app_name, R.menu.menu_home);
        binding.toolbar.setNavigationIcon(null);
        binding.toolbar.setOnClickListener(null);
        binding.appBar.setLiftable(true);
        binding.nestedScrollView.getBorderViewDelegate().setBorderVisibilityChangedListener((top, oldTop, bottom, oldBottom) -> binding.appBar.setLifted(!top));
        AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_FOLLOW_SYSTEM);

        EmulatorDetection emulatorDetection = new EmulatorDetection();
        boolean isEmulator = emulatorDetection.isDetected();
        String result = emulatorDetection.getResult();
        Log.i("EmulatorDetection", "isEmulator: " + isEmulator + ", result: " + result);

        updateStatus(isEmulator, result);
        return binding.getRoot();
    }

    @SuppressLint("SetTextI18n")
    private void updateStatus(boolean isEmulator, String result) {
        if (isEmulator) {
            binding.statusIcon.setImageResource(R.drawable.iconsax_closecircle);
            binding.resultText.setText(result);
        } else {
            binding.statusIcon.setImageResource(R.drawable.iconsax_tickcircle);
            binding.resultText.setText("Nothing detected!");
        }
    }

    public static class AboutDialog extends DialogFragment {
        @NonNull
        @Override
        public Dialog onCreateDialog(@Nullable Bundle savedInstanceState) {
            DialogAboutBinding binding = DialogAboutBinding.inflate(getLayoutInflater(), null, false);
            setupAboutDialog(binding);
            return new BlurBehindDialogBuilder(requireContext()).setView(binding.getRoot()).create();
        }

        private void setupAboutDialog(DialogAboutBinding binding) {
            binding.designAboutTitle.setText(R.string.app_name);
            binding.designAboutInfo.setMovementMethod(LinkMovementMethod.getInstance());
            binding.designAboutInfo.setTransformationMethod(new LinkTransformationMethod(requireActivity()));
            binding.designAboutInfo.setText(HtmlCompat.fromHtml(getString(
                    R.string.about_view_source_code,
                    "<b><a href=\"https://t.me/revenyy\">Telegram</a></b>",
                    "<b><a href=\"https://github.com/reveny/\">Reveny</a></b>"), HtmlCompat.FROM_HTML_MODE_LEGACY));
            binding.designAboutVersion.setText(String.format(LocaleDelegate.getDefaultLocale(), "%s (%d)", BuildConfig.VERSION_NAME, BuildConfig.VERSION_CODE));
        }
    }


    private void showAbout() {
        // Showing the About Dialog
        new AboutDialog().show(getChildFragmentManager(), "about");
    }


    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}