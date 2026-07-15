### jitter ###
What can you say about the jitter (deviation in time) introduced when extending the maximum real time measured in NORMAL MODE? 

Cand exitinzi timpul prin numararea overflow-urilor, apare o latenta foarte mica, datorata faptului ca  IRS(interrupt Service Routine) nu e apelata niciodata instant.
Atata timp cat rutina e scurta si nu exista blocari de intreruperi, acest jitter ar trebui sa fie nesemnificativ.
