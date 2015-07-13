import serial
import wx


class ImagePanel(wx.Panel):

    def __init__(self, parent, image):
    	wx.Panel.__init__(self, parent)
    	self.frame = parent
    	self.image = image

        self.Bind(wx.EVT_CHAR, self.on_keypress)
    	self.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
    	self.Bind(wx.EVT_ERASE_BACKGROUND, self.draw_image)

    def draw_image(self, event):
    	"""
    	Draws the image to the panel's background.
    	"""
    	dc = event.GetDC()
    	if not dc:
            dc = wx.ClientDC(self)
            rect = self.GetUpdateRegion().GetBox()
            dc.SetClippingRect(rect)
        dc.Clear()
        # frame_size = self.frame.GetSizeTuple()
        # height = (frame_size[0] / 2) - self.image.GetHeight()
        # width = (frame_size[1] / 2)
        dc.DrawBitmap(self.image, 0, 0)
    	self.SetFocus()
        print("image drawn?")

    def on_keypress(self, event):
    	"""
    	Handles key press events.
    	"""
        keycode = event.GetKeyCode()
    	if keycode == wx.WXK_ESCAPE:
    	    self.frame.close()
    	else:
    	    self.frame.switch_image(chr(keycode))


class MainFrame(wx.Frame):

    def __init__(self, parent):
        wx.Frame.__init__(self, parent)
        self.ShowFullScreen(True, style=wx.FULLSCREEN_ALL)
        self.Show()

        self.image = wx.Bitmap('./images/rfid_main.jpg')
        self.panel = ImagePanel(self, self.image)

	       # Setup image map
        filename = 'image_list.txt'
        lines = (line.rstrip('\n') for line in open(filename))
        self.image_map = {}
        for line in lines:
            self.image_map[line[0]] = line[2:]

    	# Listen for Arduino
    	serial.Serial('/dev/tty.usbmodemfa131', baudrate=9600)

        # Timer to switch back to start image
        self.timeout = 600000  # 10 min
        self.timeout_timer = wx.Timer(self, wx.ID_ANY)
        self.start_timeout_timer()

        # serial.Serial('/dev/tty.usbmodemfa131', baudrate=9600)

    def start_timeout_timer(self):
        """
        Timer for the start image.
        """
        self.Bind(wx.EVT_TIMER, self.switch_on_timeout, self.timeout_timer)
        self.timeout_timer.Start(self.timeout)

    def restart_timeout_timer(self):
        """
        Stops then restarts the timeout timer.
        """
        self.timeout_timer.Stop()
        self.start_timeout_timer()

    def switch_image(self, char):
    	"""
    	Switches the image.
    	"""
        self.image = wx.Bitmap('./images/' + self.image_map[char])
        self.panel.image = self.image
        self.panel.GetEventHandler().ProcessEvent(wx.EraseEvent())
        self.restart_timeout_timer()

    def switch_on_timeout(self, event):
        """
        Switches the current image frame to the base image.
        """
        self.image = wx.Bitmap('./images/rfid_main.jpg')
        self.panel.image = self.image
        self.panel.GetEventHandler().ProcessEvent(wx.EraseEvent())
        self.restart_timeout_timer()

    def close(self):
        """
        Closes the frame.
        """
        self.Destroy()


app = wx.App(False)
MainFrame(None)
app.MainLoop()
