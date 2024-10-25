import cv2
import tkinter as tk
from tkinter import Label, Button, Frame
from PIL import Image, ImageTk

# Initialize tkinter window
root = tk.Tk()
root.title("Full-Screen Video Player")

# Make the window full screen
root.attributes('-fullscreen', True)

# Create a frame for the video (full screen) and button frame at the bottom
video_frame = Frame(root, bg="black")
video_frame.pack(fill=tk.BOTH, expand=True)

button_frame = Frame(root, bg="gray")
button_frame.pack(fill=tk.X, side=tk.BOTTOM)

# Create a Label to display the video inside the video_frame
video_label = Label(video_frame, bg="black")
video_label.pack(fill=tk.BOTH, expand=True)

# Load video using OpenCV
cap = cv2.VideoCapture("video.mp4")

# Variables to control playback
is_playing = False
frame_pos = 0
fps = 120  # Desired FPS for video playback

# External functions to handle Start, Stop, and Reset
def start_video():
    global is_playing
    is_playing = True
    play_video()  # Begin playing video

def stop_video():
    global is_playing
    is_playing = False

def reset_video():
    global frame_pos, is_playing
    is_playing = False
    frame_pos = 0
    cap.set(cv2.CAP_PROP_POS_FRAMES, 0)  # Reset to first frame
    show_frame()  # Show the first frame after resetting

# Function to display each frame of the video
def play_video():
    global frame_pos
    if is_playing:
        ret, frame = cap.read()
        if ret:
            frame_pos += 1
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            # Get the width and height
            width = video_label.winfo_width()
            height = video_label.winfo_height() - 50  # Reduce height by 50 pixels

            # Check dimensions before resizing
            if width > 0 and height > 0:
                img = Image.fromarray(frame)
                img = img.resize((width, height), Image.ANTIALIAS)
                imgtk = ImageTk.PhotoImage(image=img)

                video_label.imgtk = imgtk
                video_label.configure(image=imgtk)

                video_label.after(int(1000 / fps), play_video)
            else:
                video_label.after(100, play_video)  # Try again after a short delay
        else:
            stop_video()  # Stop if video ends
    else:
        cap.set(cv2.CAP_PROP_POS_FRAMES, frame_pos)  # Pause at the current frame

# Show a specific frame (useful for resetting or stopping)
def show_frame():
    ret, frame = cap.read()
    if ret:
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Get the width and height
        width = video_label.winfo_width()
        height = video_label.winfo_height() - 50  # Reduce height by 50 pixels

        # Check dimensions before resizing
        if width > 0 and height > 0:
            img = Image.fromarray(frame)
            img = img.resize((width, height), Image.ANTIALIAS)
            imgtk = ImageTk.PhotoImage(image=img)

            video_label.imgtk = imgtk
            video_label.configure(image=imgtk)
        else:
            video_label.after(100, show_frame)  # Try again after a short delay

# Exit full screen and close the application
def exit_fullscreen(event=None):
    root.attributes('-fullscreen', False)
    root.quit()

# Create Start, Stop, and Reset buttons
start_button = Button(button_frame, text="Start", command=start_video)
stop_button = Button(button_frame, text="Stop", command=stop_video)
reset_button = Button(button_frame, text="Reset", command=reset_video)

# Position buttons at the bottom
start_button.pack(side=tk.LEFT, padx=10, pady=5)
stop_button.pack(side=tk.LEFT, padx=10, pady=5)
reset_button.pack(side=tk.LEFT, padx=10, pady=5)

# Bind ESC key to exit full screen
root.bind("<Escape>", exit_fullscreen)

# Display the first frame initially
reset_video()

# Run the tkinter main loop
root.mainloop()
