C = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
Cx = [];
M = [error];

R = [];

for i = 1:length(M)-32
    if M(i) == 1
      Cx = [zeros(1,i-1) C zeros(1,(length(M)-length(C)-i+1))];
      R = bitxor(M,Cx);
      M = R;
    end
end
R