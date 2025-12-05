// To restore your original (global) git username and email after changing them locally for Chromium setup, run:
// Replace "Your Name" and "you@example.com" with your original values.

git config --global user.name "Your Name"
git config --global user.email "you@example.com"

// (Optional) If you also set a local config in the Chromium repo folder that should revert to global, you can unset:
git config --unset --local user.name
git config --unset --local user.email

// After this, global config will be used for any repo (unless you again set something different locally).
