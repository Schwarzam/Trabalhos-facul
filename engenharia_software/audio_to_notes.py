import pyaudio
import numpy as np

# Define constants
CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100

# Function to map frequency to note
def frequency_to_note(frequency):
    NOTES = 'C C# D D# E F F# G G# A A# B'.split()
    if frequency < 16.35:
        return "Note out of range"
    note_num = 12 * np.log2(frequency / 16.35)
    rounded_note_num = int(round(note_num))
    octave = rounded_note_num // 12
    note_index = rounded_note_num % 12
    return f"{NOTES[note_index]}{octave}"

# Initialize PyAudio
audio = pyaudio.PyAudio()

stream = audio.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)

print("Recording...")

try:
    while True:
        data = stream.read(CHUNK)
        numpydata = np.frombuffer(data, dtype=np.int16)
        fft_data = np.fft.fft(numpydata)
        frequencies = np.fft.fftfreq(len(fft_data))

        # Get the index of the peak frequency
        peak_index = np.argmax(np.abs(fft_data))
        peak_frequency = abs(frequencies[peak_index] * RATE)

        # Map frequency to note
        note = frequency_to_note(peak_frequency)
        print("Detected note:", note)

except KeyboardInterrupt:
    print("Stopped")

finally:
    stream.stop_stream()
    stream.close()
    audio.terminate()

