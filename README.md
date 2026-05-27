# NOVEK Technical Assessments

This repository contains my submissions for the NOVEK engineering technical assessments, covering both Sheet Metal CAD design and an embedded IoT control system simulation.

## Test 1: Sheet Metal CAD Design & Fabrication

**Objective:** To design and model the exterior body of a commercial ice maker (500mm x 600mm x 830mm) using sheet metal best practices and generate fabrication-ready drawings.

### Design Execution:
* Modeled completely in Autodesk Inventor Professional 2024 using a uniform 1.2mm stainless steel sheet thickness.
* Engineered a realistic 5-part assembly (Main Wrapper, Base Tray, Front Panel, Back Panel, and Internal Stiffener) rather than a monolithic part to ensure physical manufacturability.
* **Engineering Feature:** Incorporated a custom internal U-channel stiffener behind the front ventilation louvers to reinforce structural integrity and prevent panel warping after laser cutting.
* Included realistic backend cutouts for power input, water line and an active compressor exhaust fan shroud.

### Fabrication Details:
1. **Total bends in design:** 12
2. **Max bends on a single part:** 4
3. **Total parts requiring bending:** 5

### Deliverables Included :
* `Novek_Ice_Maker.pdf`: Full 2D multi-sheet engineering drawing package scaled to A4 size, featuring overall dimensions and flat patterns with automated bend annotations.
* `Nurxiovo_Ice_Maker_Assembly.step`: Standardized geometric export for manufacturing verification.
* `Novek_Ice_Maker_PackAndGo.zip`: Complete Autodesk Inventor project archive bundle containing all linked parts (.ipt), assembly (.iam), and project mapping (.ipj) files.

---

## Test 2: Proteus IoT Motor Control & Telemetry System

**Objective:** Develop a firmware routine controlling a cooling fan motor based on a specific temperature threshold using a DHT11 sensor, alongside an automated remote telemetry routine pushing JSON payloads to a cloud endpoint over an active GPRS/SIM connection.

### Hardware Substitution Note:
* **Modem Utilized:** SIM900D GSM Module (Substituted for the requested SIMCOM SIM800L due to component availability within the Proteus workspace library). The underlying firmware architecture remains identical as both modems share equivalent AT command structures for GPRS profile initializations and secure HTTP transport actions.

### Deliverables Included :
* `fan_control_system.ino`: Refactored production-ready Arduino firmware code optimized for low-latency loop execution.
* `proteus_circuit_schematic.pdsprj`: Complete workspace file containing microcontroller wiring, virtual terminal debug hooks, and simulated peripheral test loads.
