# TODO lists

## General remarks
- see also `//TODO`- comments in the c++ code (can be checked in CLion)
- Include tests for all items

## Opgaves
- [ ] Finish
	- [x] Wegen en voertuigen inlezen
	- [x] Wegennetwerk inlezen
	- [x] Simpele uitvoer
	- [x] Rijden van voertuigen
	- [x] Automatische simulatie

	- [x] 1.3. Voertuig met Type inlezen
	- [x] 1.4. Wegen met verkeertekens inlezen
	- [x] 1.5. Meerdere rijstroken
	- [x] 2.2. Grafische impressie
	- [x] 3.3. Rijden van voertuig met type
	- [x] 3.4. Simulatie van baan met zones
	- [x] 3.5. Simulatie van baan met bushaltes
	- [x] 3.6. Simulatie van baan met verkeerslichten

	- [ ] TESTSTESTSTESTS

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
	- [x] get, set, remove connection
	- [x] add, remove, get/traverse car(s)
	- [x] provide location-based iterator for vehicles

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

- [ ] Serialiser
 	- [x] Output to ostream
 	- [x] Default mode
 	- [ ] ASCII mode

## tests
- [ ] class: RoadSystem
	- [ ] load simulation
	- [ ] dump simulation
	- [ ] start simulation
	- [ ] advance simulation
	- [ ] add, get/traverse car(s)
	- [ ] add, get/traverse road(s)
	- [ ] simulation empty?
	- [ ] simulation active?

- [x] class: Road
	- [x] get & set name
	- [x] get & set length
	- [x] get, set, remove connection
	- [x] add, has?, get/traverse car(s)
	- [x] provide location-based iterator for vehicles

- [x] class: Vehicle
	- [x] get & set licence plate
	- [x] get & set road
	- [x] get& set acceleration
	- [x] get & set speed
	- [x] get & set position

- [ ] class: Vehicle::Car
	- [ ] update

- [ ] Serialiser
	- [ ] Output to ostream
	- [ ] Default mode
	- [ ] ASCII mode
	
