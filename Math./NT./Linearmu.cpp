const int N=101;
int mu[N],pr[N];
 
void pre(){
	rep(i,0,101){
		pr[i]=1;
		mu[i]=1;
	}
	pr[1] = 0;
	rep(i,2,101){
		if(pr[i]){
			mu[i]=-mu[i];
			for(int j = 2 ; j*i<=100 ;j++){
				pr[i*j] = 0 ;
				if(j%i==0) mu[i*j]=0;
				else mu[i*j] =-mu[i*j];
			}
		}
		
	}
}
