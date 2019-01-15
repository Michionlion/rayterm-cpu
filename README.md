# `RayTerm`

A Ray-Tracing Graphics Engine for XTerm-like Terminals

## Development

Use `gradle build` to build the project, and execute a binary located inside `build` to run it.

The `run.sh` script builds and then runs the built binary automatically. However, it starts a new `xterm` window explicitely, with preset geometry and position. Additionally, the title is set to `i3-float`, which can be used to make the window automatically float when opened by using the following lines (if you are using the i3 window manager) in your i3 configuration:

```
for_window [title="i3-float"] floating enable border pixel 2
```

Similar scripts can be made by using `run.sh` as a reference for other terminals or window managers.
