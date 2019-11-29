load ('inputdata')
C = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
Cx = [];
M = [packet zeros(1,32)];
X = [1 zeros(1,12031)];
X2 = X ;
R = [];
error2 = [zeros(1,length(X))];


for k = 5:32
    for j = 1:12000
      if X(j) == 1
        Cx = [zeros(1,j-1) C zeros(1,(length(X)-length(C)-j+1))];
        error2 = bitxor(X,Cx);
        X = error2;
        error = bitxor(X2,error2);
      end
    end
    X(k) = 1;
    X2 = X;
    sum(error)
end

save ('hw2_104061124','error','-append');

    