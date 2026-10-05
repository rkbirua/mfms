# Git coordination

Repository: https://github.com/rkbirua/mfms

Each member works on their own branch and commits their own reviewed work. Keep
existing history. Do not rewrite authors, force-push shared branches or upload the
entire project in one replacement commit.

```sh
git switch main
git pull --ff-only
git switch -c your-name-task
# Edit and test your files.
git add path/to/your/files
git commit -m "Describe the change"
git push -u origin your-name-task
```

Open a pull request to main with the behaviour changed and test results. A group
member reviews the change before merging. Prefer a regular merge commit when
preserving each member's individual commits is important. Resolve conflicts by
checking both implementations; run the complete test suite after integration.
Do not merge unrelated branches without inspecting their changes.

Before submission, review open pull requests with module owners, run the full
test suite after merges and confirm the README roster. Include the repository
URL and technical report in the Moodle hand-in. A branch or pull request does
not mean the changes have already been merged or submitted to Moodle.
