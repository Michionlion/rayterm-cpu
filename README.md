# `RayTerm`

A Ray-Tracing Graphics Engine for XTerm-like Terminals

## Development

The Google Test binary must be built before running or compiling `Rayterm`.
This can be done with `gradle buildGoogleTest`. Then `gradle build` can be used
to build the project. To run `RayTerm` either execute a binary located inside
`build`, or execute the `run.sh` script.

The `run.sh` script builds and then runs the built binary automatically.
However, it starts a new `xterm` window explicitly, with preset geometry and
position. Additionally, the title is set to `i3-float`, which can be used to
make the window automatically float when opened by entering the following
line (if you are using the i3 window manager) in your i3 configuration:

```text
for_window [title="i3-float"] floating enable border pixel 2
```

Similar scripts can be made by using `run.sh` as a reference for other
terminals or window managers.
