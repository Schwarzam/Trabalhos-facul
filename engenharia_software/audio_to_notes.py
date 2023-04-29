import pyaudio
import numpy as np

# Define constants
CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100

# Function to map frequency to note
def frequency_to_note(frequency):
    # Define the notes in an octave as a list of strings
    NOTES = 'C C# D D# E F F# G G# A A# B'.split()
    
    # If the frequency is below the lowest note on a piano (16.35 Hz, which is C0),
    # return "Note out of range"
    if frequency < 16.35:
        return "Note out of range"
    
    # Calculate the note number using the formula:
    # note_num = 12 * log2(frequency / reference_frequency)
    # where the reference_frequency is 16.35 Hz (the frequency of C0)
    note_num = 12 * np.log2(frequency / 16.35)
    
    # Round the note number to the nearest integer to find the closest note
    rounded_note_num = int(round(note_num))
    
    # Calculate the octave of the note by integer-dividing the rounded_note_num by 12
    # (since there are 12 notes in an octave)
    octave = rounded_note_num // 12
    
    # Calculate the index of the note within the octave by taking the modulo of
    # the rounded_note_num and 12
    note_index = rounded_note_num % 12
    
    # Return the note as a formatted string, e.g., "C4", by looking up the note name
    # using the note_index and appending the octave
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

