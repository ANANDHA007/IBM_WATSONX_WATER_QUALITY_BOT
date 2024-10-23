Water Quality Monitoring and AI-Powered Chatbot
# **Overview**
This project leverages IBM watsonx Assistant to create an intelligent chatbot that provides detailed insights into water quality metrics. The solution aligns with Sustainable Development Goal 6 (SDG 6) by supporting clean water and sanitation through real-time data and meaningful analysis.
# **Features**
\- Real-time water monitoring using IoT sensors for multiple water quality parameters.
\- Waterbody and species viability assessment: Identify fish species and crops suited to specific regions.
\- Disease prediction: Provides insights into waterborne diseases affecting particular areas.
\- Top/bottom ranking of water quality: Identifies the best and worst water quality areas.
\- Pure water source tracking: Locates the most potable water sources.
# **Project Structure**

.
├── API
│   ├── controllers/        # Handles logic for API endpoints
│   ├── models/             # Database models for water data
│   ├── routes/             # API routes definitions
│   ├── node\_modules/       # Dependencies for the backend
│   ├── app.js              # Main backend server code
│   ├── package.json        # Backend dependencies
│   └── package-lock.json   # Dependency tree lock file
├── Hardware
│   ├── GravityTDS-master/  # TDS sensor library
│   ├── Node\_to\_Database/   # IoT data upload scripts
│   ├── Sensor\_Data\_Tests/  # Test cases for sensor accuracy
│   ├── Turbidity\_Sensor-master/ # Turbidity sensor library
│   └── node\_modules/       # Dependencies for hardware interfacing
# **How it Works**
1\. IoT Sensor Data Collection
`   `Sensors deployed at multiple locations gather real-time metrics (pH, temperature, TDS, and turbidity).
2\. Data Upload to Backend
`   `IoT modules push the collected data to the Node.js backend, which stores the data in a connected database.
3\. Integration with IBM watsonx Assistant
`   `- Backend Exposure: The Node.js app is exposed to the internet using ngrok.
`   `- Webhook Communication: The chatbot interacts with the backend to fetch water-related information.
4\. User Interaction with Chatbot
`   `Users can ask the chatbot about water quality, viable species, waterborne diseases, and more.
# **Installation and Setup**
## **Backend Setup**
1\. Clone the repository:
`   `git clone <repository\_url>
`   `cd WaterQualityChatbot
2\. Install dependencies:
`   `cd API
`   `npm install
3\. Start the backend server:
`   `node app.js
4\. Expose the backend using ngrok:
`   `ngrok http 808
5\. Use the ngrok public URL in the webhook configuration of IBM watsonx Assistant.
## **Hardware Setup**
1\. Install required sensor libraries in the Hardware section.
2\. Connect sensors to the IoT device (e.g., NodeMCU).
3\. Run the data upload script:
`   `node Node\_to\_Database/upload.js
# **Technologies Used**
\- Node.js: Backend server and API handling
\- IBM watsonx Assistant: AI-powered chatbot
\- ngrok: Public URL tunneling for backend exposure
\- IoT Sensors: pH, temperature, TDS, and turbidity sensors
-PostgreSQL: Database for storing water quality data
# **Use Cases**
\- Fisheries: Identify water conditions suitable for fish species.
\- Agriculture: Recommend crops based on water quality.
\- Disease Control: Alert about waterborne disease risks.
\- Water Management: Identify areas with optimal or poor water quality.
# **Contributing**
We welcome contributions! Please follow these steps:
1\. Fork the repository.
2\. Create a new branch (`git checkout -b feature/your-feature`).
3\. Commit your changes (`git commit -m "Add your feature"`).
4\. Push to the branch (`git push origin feature/your-feature`).
5\. Open a pull request.
# **License**
This project is licensed under the MIT License - see the LICENSE file for details.
# **Acknowledgments**
Special thanks to:
\- IBM watsonx Assistant for chatbot capabilities.
\- ngrok for seamless backend exposure.
\- Sensor providers for IoT hardware.
# **Contact**
For more information, contact Team Sentinels at teamsentinelssalem@gmail.com
