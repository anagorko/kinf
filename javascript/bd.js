var nic  = "black";
var ziemia = "brown";
var kamien = "gray";

var stany = Array( nic, ziemia, kamien );
					
function setupBoard()
{	
}

function calculateNewState(x,y)
{
	var teraz = cellState(x,y);
	var pozniej;

	if (teraz == ziemia) {
		pozniej = ziemia;
	}
	
	if (teraz == nic) {
		if (cellState(x,y-1) == kamien) {
			pozniej = kamien;
		} else if (cellState(x,y-1) == nic) {
			if (cellState(x+1,y) == kamien && cellState(x+1,y-1) == kamien) {
				pozniej = kamien;
			} else if (cellState(x-1,y) == kamien && cellState(x-1,y-1) == kamien
					  &&!(cellState(x-2,y) == nic && cellState(x-2,y-1) == nic)) {
				pozniej = kamien;
			} else {
				pozniej = nic;
			}
		} else {
			pozniej = nic;
		}
	}
	
	if (teraz == kamien) {
		if (cellState(x,y+1) == nic) {
			pozniej = nic;
		} else if (cellState(x,y+1) == kamien) {
			if (cellState(x-1,y) == nic && cellState(x-1,y+1) == nic) {
				pozniej = nic;
			} else if (cellState(x+1,y) == nic && cellState(x+1,y+1) == nic
					   && !(cellState(x+2,y) == kamien && cellState(x+2,y+1) == kamien)) {
				pozniej = nic;
			} else {
				pozniej = kamien;
			}
		} else {
			pozniej = kamien;
		}
	}
	
	return pozniej;
}
