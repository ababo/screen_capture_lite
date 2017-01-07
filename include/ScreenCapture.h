#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <string>

namespace SL {
	namespace Screen_Capture {
		
		struct Monitor{
			int Id;
			int Height;
			int Width;
			//Offsets are the number of pixels that a monitor can be from the origin. For example, users can shuffle their monitors around so this affects their offset.
			int OffsetX;
			int OffsetY;
			std::string Name;
		};
		
		struct ImageRect {
			int    left = 0;
			int    top = 0;
			int    right = 0;
			int    bottom = 0;
		};
		std::vector<Monitor> GetMonitors();
		//the pointers to start data are to the beginning of the ENTIRE image so the callback for the dif is called, users must calculate the correct data to copy out. See the examples directory on how to do this.
		typedef std::function<void(const char* startdata, const int pixelstride /*in bytes*/, const Monitor& monitor)> CaptureEntireMonitorCallback;
		typedef std::function<void(const char* startdata, const int pixelstride /*in bytes*/, const Monitor& monitor, const ImageRect& rect)> CaptureDifMonitorCallback;

		class ScreenCaptureManagerImpl;
		class ScreenCaptureManager {
			std::unique_ptr<ScreenCaptureManagerImpl> _ScreenCaptureManagerImpl;

		public:
			ScreenCaptureManager();
			~ScreenCaptureManager();
			//Set which monitors should be captured. This allows users to capture only a specific monitor, or all
			void Set_CaptureMonitors(const std::vector<Monitor>& monitorstocapture);
			//set this callback if you want to capture the entire Montitor each new frame
			void Set_CapturCallback(CaptureEntireMonitorCallback img_cb);
			//set this callback if you want to capture just differences between the frames
			void Set_CapturCallback(CaptureDifMonitorCallback img_cb);

			void StartCapturing(int min_interval);
			void StopCapturing();
		};		
		const int PixelStride = 4;
	
    }
}