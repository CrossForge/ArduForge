/*****************************************************************************\
*                                                                           *
* File(s): OpticalLightBarrierESP32.h and OpticalLightBarrierESP32.cpp      *
*                                                                           *
* Content: An emulation of a light barrier using a camera sensor.           *
*                                                                           *
*                                                                           *
*                                                                           *
* Author(s): Tom Uhlmann                                                    *
*                                                                           *
*                                                                           *
* The file(s) mentioned above are provided as is under the terms of the     *
* MIT License without any warranty or guaranty to work properly.            *
* For additional license, copyright and contact/support issues see the      *
* supplied documentation.                                                   *
*                                                                           *
\****************************************************************************/

#ifndef __OPTICALLIGHTBARRIERESP32_H__
#define __OPTICALLIGHTBARRIERESP32_H__

// works only with an ESP32
#ifdef ESP32

#include "ESP32Camera.h"

namespace ArduForge{
    /**
     * @brief With this module a light barrier can be emulated using a camera sensor. It has been developed for the ESP32 camera module (AI Thinker type) using an OV2640 camera.  
     * 
     * Your typical light barrier sensor (e.g. time of flight, 10€ per piece + controller) only works at a range of a few centimeters up to a few meters under optimal conditions. Sensor with larger measuring range get pretty expensive and are not consumer grade equipment anymore. With an ESP32 Camera module (about 6€ each, including Microcontroller) we can build a fully functional light barrier. Due to the comparably low FPS of a camera module the time resolution is quite limited. During tests I achieved stable 26 FPS (grayscale images) which means a reliable time resolution of 38.47 milliseconds.
     * @note This class requires exclusive access to the camera during its time of operation.
     */
    class OpticalLightBarrierESP32{
    public:
        enum BarrierMsg: uint8_t{
            BMSG_UNKNOWN = 0,               ///< Invalid Message
            BMSG_INITIALIZATION_FINISHED,   ///< Initialization finished, barrier ready to go
            BMSG_INITIALIZATION_FAILED,     ///< Something went wrong during initialization
            BMSG_CALIBRATION_FINISHED,      ///< Sensor calibration finished
            BMSG_BARRIER_TRIGGERED,         ///< The barrier was triggered
        };//BarrierMsg

        /**
         * @brief State enumeration.
         */
        enum ActiveState: uint8_t{
            STATE_NONE = 0,       ///< No operation (idle)
            STATE_CALIBRATION,    ///< Calibration mode
            STATE_START_DETECION, ///< Prepare and enter detection state
            STATE_STOP_DETECTION,
            STATE_DETECTION,      ///< Detection mode
        };//ActiveOperation

        /**
         * \brief Prototype of the callback function.
         */
        typedef void (*BarrierCallbackFunc)(BarrierMsg, void*);

        /**
         * @brief Constructor
         */
        OpticalLightBarrierESP32(void);

        /**
         * @brief Destructor
         */
        ~OpticalLightBarrierESP32(void);

        /**
         * @brief Start the optical light barrier.
         * 
         * @param[in] BarrierCB Callback function where all events will be relayed to.  
         * @param[in] Sensitivity Barrier sensitivity relative to the camera sensor's noise level. 
         * @param[in] CameraThreadCoreID Which core to use for the camera thread.
         */
        void begin(BarrierCallbackFunc BarrierCB, void *pUserCBParam = nullptr, float Sensitivity = 1.3f, uint8_t CmaeraThreadCoreID = 0);

        /**
         * @brief Shut down optical light barrier. Releases camera.
         */
        void end(void);

        /**
         * @brief Calibrate sensor (estimate noise level).
         * 
         * Frames are captured for a small amount of time and the deviation between them is calculated. The average deviation over the capture time will be the sensor noise level. Noise depends significantly on the lighting condition. Low levels of light cause higher noise.
         * @param[in] Duration Time in milliseconds for the calibration process. Should be at least 1000 to get an acceptable result.
         */
        void calibrate(uint16_t Duration = 2000);

        /**
         * @brief Barrier enters the detection mode. It will use the noise estimate from the last OpticalIghtBarrier::calibrate call.
         */
        void startDetection(void);

        /**
         * @brief Stops detection mode and puts the barrier in idle mode.
         */
        void stopDetection(void);

        /**
         * @brief Returns current sensitivity value:
         * @return Current sensitivity value.
         */
        float sensitivity(void)const;

        /**
         * @brief Sets new sensitivity value.
         * @param[in] Sensitivity New sensitivity value.
         */
        void sensitivity(float Sensitivity);

        /**
         * @brief Returns frames per second the detection is currently running. Only valid if state is STATE_DETECTION
         * 
         * @return Current fps.
         */
        uint8_t fps(void)const;

        /**
         * @brief Current state of the device. @see ActiveState
         * 
         * @return Current state.
         */
        ActiveState state(void)const;

        uint32_t imageSize(void)const;
        void captureImage(uint32_t *pWidth, uint32_t *pHeight, uint8_t *pImgData, bool AugmentCaptureLine);
        float noise(void)const;

    protected:

        /**
         * @brief Defines a single optical barrier line and its image data.
         * 
         * From a given image the pixel data in the middle and \f$\pm\f$ Magnitude lines will be extracted. If the deviation of pixel values is larger than a threshold value the barrier is broken and an event is triggered.
         * @note The camera is assumed to be aligned with the barrier line in portrait mode so we can use more pixels.
         * 
         */
        struct BarrierLine{
            uint8_t *pBuffer;   ///< Image data (RGB565 values).
            uint8_t Magnitude;  ///< Width in lines of the barrier.
            uint16_t LineSize;  ///< Size (number of pixels) of a single line.

            /**
             * @brief Computes deviation value between two barrier lines with a linear function.
             * 
             * @param[in] pLeft Barrier line 1.
             * @param[in] pRight Barrier line 2.
             * @return Linear deviation value.
             */
            static float computeDeviationLinear(BarrierLine *pLeft, BarrierLine *pRight);

            /**
             * @brief Computes deviation value between two barrier lines with a quadratic function. 
             * 
             * @param[in] pLeft Barrier line 1.
             * @param[in] pRight Barrier line 2.
             */
            static float computeDeviationQuadratic(BarrierLine *pLeft, BarrierLine *pRight);

            /**
             * @brief Constructor
             */
            BarrierLine(void);

            /**
             * @brief Destructor
             */
            ~BarrierLine(void);

            /**
             * @brief Initializes the barrier line (allocates buffer).
             * 
             * @param[in] Magnitude \f$\pm\f$ number of lines from the middle that should also be considered.
             * @param[in] LineSize Size (number of pixels) of a single line.
             */
            void init(uint8_t Magnitude, uint16_t LineSize);

            /**
             * @brief Clears data.
             */
            void clear(void);

            /**
             * @brief Extracts required image data from a picture frame.
             * 
             * @param[in] pFB Image frame. Can not be null.
             */
            void extractData(camera_fb_t *pFB);

            static void augmentCaptureLine(uint8_t Magnitude, uint32_t Width, uint32_t Height, uint8_t *pImgData);


        };//BarrierLine


        /**
         * @brief Camera thread function.
         * 
         * @param pParam Pointer to the parent instance of OpticalLightBarrierESP32.
         */
        static void cameraThread(void *pParam);

        BarrierCallbackFunc m_Callback; ///< Callback method to which messages will be delivered.
        void *m_pUserCBParam;           ///< User parameter that will be relayed to the callback function.

        TaskHandle_t m_hCameraThread;   ///< Camera thread handle.
        bool m_StopThread;              ///< Kill switch for the camera thread.

        float m_Sensitivity;            ///< Barrier sensitivity
        float m_Noise;                  ///< Sensor's estimated noise value.
        uint16_t m_CalibrationDuration; ////< Duration in milliseconds the calibration is allowed to take.
        ActiveState m_ActiveState;      ///< Current state of the optical light barrier.
        uint8_t m_FPS;                  ///< Current FPS value.
        uint8_t m_LineMagnitude;        ///< Line Magnitude
    };//OpticalLightBarrierESP32

}//name-space


#endif // ESP32
#endif // Header-Guard