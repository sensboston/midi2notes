# midi2notes

This simple helper will generate class from selected midi file and allow you to play synthetic music using PWM modulation on ESP32-based boards.
Class name will generated from midi file name (without extension) so to avoid long and messy name, rename your midi file first.
Example: **midi2notes.exe Tetris.mid > tetris.h**

Check ArduinoExample folder for working sketch.

To produce pseudo "polyphonic" sound, you may connect not one but many pins to the speaker (as shown on video). But remember, it's just a PWM generated tones, not a real midi syntheser! To achieve better results, I recommend to tweak generated player classes, leaving just a significant and well sounding channels.

Here is video of playing example:
<div align="center">
  <a href="https://www.youtube.com/watch?v=n94EGgIgxp4"><img src="https://img.youtube.com/vi/n94EGgIgxp4/0.jpg" alt="Car starter in action"></a>
</div>
