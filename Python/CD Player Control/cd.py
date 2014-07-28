import ctypes

ctypes.windll.WINMM.mciSendStringW(u"set cdaudio door open", None, 0, None)