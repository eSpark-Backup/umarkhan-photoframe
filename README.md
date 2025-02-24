# Digital Photo Frame
#### Client Name: Umar Khan

## Project Requirements
### Hardware Requirements
The product is a digital photo frame that requires below components:
- **223 Programmable / Addressable LED lights** configured by a GET response from a external API endpoint from a cloud server.
    - 5mm - placed at the centre of the markers
    - SMD - So it can be assembled by a robot and minimum manual work like soldering
    - Programmable/Addressable - Dimmable, On/Off
    - 4 colours minimum - Red, Green, Blue, Yellow
- A small LCD screen preferably **101.6mm x 76.2mm** which show the data provided by the GET response around 3/4 rows of text at one time.
- **Desired Dimensions: 704mm x 370mm**. Enclosed in a Wooden Frame.
- Wi-Fi connectivity: The electronics needs to be able to connect to the users WiFi.
- Powered by USBC adaptor.
- On/Off switch.
- 3 toggle switch (Low Medium High) settings for the LED.
- Height of components to not exceed LED to allow for picture frame plate / encasing to sit flush. LCD selection has to be done very carefully so as to not expose it too much from the frame.
- 
### Firmware Requirements
- Some features outlined in **Hardware Requirements** section.
- The text strings should vertically scroll on the screen on repeat with a short interval (around 2 seconds).
- OTA firmware updates (endpoint details will be provided).
- Interval for pinging API to be changeable by code (10 mins for MVP). This ping API is to ping the server to update health status.
- Scheduled on/off by settings (based on timing the user can set) through a hosted Webpage.
- Offline mode: When there's no Wi-Fi connection, the device should run a pre-programmed sequence similar to the API response (to be provided later).
- LCD Screen on the bottom should always show the current time and timezone - automatically picked up. Or configurable by the user by webpage similar to the wifi settings.
- Device connect to WiFi Gateway via details entered by user on locally hosted webpage. 
