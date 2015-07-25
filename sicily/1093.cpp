#include <iostream>

#define MIN 0x3f3f3f3f

using namespace std;

int main(){

    int w[5], r[5];
    int cont = 1;

    while(cin >> w[1] >> r[1]){

        for(int i = 2; i <= 3; i++) {
            cin >> w[i] >> r[i];
	}
        cin >> r[4];
        w[0] = 0, w[4] = 1000;
        int wt;
        cout << "Set number " << cont++ <<":" <<endl;

        while(cin >> wt && wt){

            int min_p = MIN, min_a;
            for(int i = 1; i <= 4 ; i++){
                if(wt <= w[i]){
                    if(wt >= w[i-1]+1){
                        min_p = wt * r[i];
			min_a = 0;
		    } else {
			if (min_p > (w[i-1]+1) * r[i]) {
			    min_p = (w[i-1]+1) * r[i];
			    min_a = w[i-1]+1-wt;
			} 
		    }
		}
	    }
	    cout << "Weight (" << wt << ") has best price $" << min_p << " (add " << min_a << " pounds)" <<endl;
	}
	cout << endl;
    }
}
