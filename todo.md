# TODO lists

## General remarks
- see also `//TODO`- comments in the c++ code (can be checked in CLion)
- Try to find a way to lock in setters to prevent editing of e.g. licence plates during the simulation
- Include tests for all items
- set up test & release targets

- [ ] main
	- [x] reading xml-file

## Opgaves
- [ ] Finish
	- [x] Wegen en voertuigen inlezen
	- [x] Wegennetwerk inlezen
	- [x] Voertuig met Type inlezen
	- [ ] Wegen met verkeertekens inlezen
	- [x] Simpele uitvoer
	- [x] Rijden van voertuigen
	- [ ] Automatische simulatie
	- [x] Rijden van voertuig met type
	- [ ] Simulatie van baan met zones
	- [ ] Simulatie van baan met bushaltes
	- [ ] Simulatie van baan met verkeerslichten

## Implementation
- [x] class: RoadSystem
	- [x] load simulation
	- [x] dump simulation
	- [x] start simulation
	- [x] advance simulation
	- [x] add, get/traverse car(s)
	- [x] add, get/traverse road(s)
	- [x] simulation empty?
	- [x] simulation active?

- [ ] class: Road
	- [x] constructor using XML-file
	- [x] get & set name
	- [x] get & set length
	- [x] get & set connection
	- [ ] add, has?, get/traverse car(s)
	- [ ] provide location-based iterator for vehicles

- [ ] class: Vehicle
	- [x] get & set licence plate
	- [x] get & set road
	- [x] get& set acceleration
	- [x] get & set speed
	- [x] get & set position
	- [x] prepare update (gathers info)
	- [x] execute update (updates info)

- [x] class: Vehicle::Car
	- [x] advance acceleration
	- [x] advance speed
	- [x] advance position
