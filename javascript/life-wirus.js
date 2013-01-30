var nic  = "black";
var komorka = "blue";	
var wirus = "red";
var leukocyt = "white";

var stany = Array( nic, komorka, wirus, leukocyt );
					
function setupBoard()
{	
	setCellState(5,5,komorka);
	setCellState(6,5,komorka);
	setCellState(7,5,komorka);
	setCellState(8,5,komorka);
	setCellState(9,5,komorka);
	setCellState(10,5,komorka);
	setCellState(11,5,komorka);
	setCellState(12,5,komorka);
	setCellState(13,5,komorka);
	setCellState(14,5,komorka);

	setCellState(10,8,wirus);
	setCellState(13,8,leukocyt);
}
		
function licz(x, y, stan)
{
	var n = 0;

	if (cellState(x-1, y-1) == stan) 	n = n + 1;
	if (cellState(x-1, y) == stan)		n = n + 1;
	if (cellState(x-1, y+1) == stan)	n = n + 1;
	if (cellState(x, y-1) == stan)		n = n + 1;
	if (cellState(x, y+1) == stan)		n = n + 1;
	if (cellState(x+1, y-1) == stan)	n = n + 1;
	if (cellState(x+1, y) == stan)		n = n + 1;
	if (cellState(x+1, y+1) == stan)	n = n + 1;
	return n;
}
			
function calculateNewState(x,y)
{
	var teraz = cellState(x,y);
	var pozniej;

	if (teraz == nic) {
		if (licz(x,y,komorka) == 3) {
			pozniej = komorka;
		} else {
			pozniej = nic;
		}
	}
	if (teraz == komorka) {
		if (licz(x,y,wirus) > 0) {
			pozniej = wirus;
		} else if (licz(x,y,komorka) == 2 || licz(x,y,komorka) == 3) {
			pozniej = komorka;
		} else {
			pozniej = nic;
		}
	}
	if (teraz == wirus) {
		if (licz(x,y,leukocyt) > 0) {
			pozniej = leukocyt;
		} else {
			pozniej = wirus;
		}
	}
	if (teraz == leukocyt) {
		if (licz(x,y,wirus) > 0) {
			pozniej = nic;
		} else {
			pozniej = leukocyt;
		}
	}

	return pozniej;
}




