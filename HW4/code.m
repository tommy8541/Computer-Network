load ('network_A') % load data
%load ('input_test')

% The code is modified from hw3.

for p = 1:100 %search from 1 to 100
    distance = zeros(100,100); %record the distance to the node 1
    node = zeros(100,100); %record node connects to each other
    node(1,p) = 1;       %ensure that it has passed it before
    for n = 1:100            %record which node connects to node 1
        if A(p,n) == 1       %if 1 means that node connects to node 1
            distance(1,n) = 1;  %distance to node 1 is 1 
            node(1,n) = 1;      %connect to node 1 representing 1
            for i = 1:100
                if A(i,p) == 0        % this if to make sure that 0 is connectionless
                    distance(i,1) = 0; 
                    node(i,1) = 0;
                end
            end
        end
    end
    
D = sum(distance);    %define the initial value

for D = 1:100
    for i = 1:100
        if (distance(1,i) == D)                  
            for j = 1:100
                if A(i,j) == 1 && node(1,j) ==0  %find whether node doesn't be found
                    distance(1,j) = D+1;         %if found, then add 1 to distance
                    node(1,j) = i;               %then node will be update                   
                end
            end
        end
    end
end
    for i = 1:100                %assign the true value into d
        d(p,i) = distance(1,i);
    end
end

for x = 1:10    %定義自己到自己的距離為0
    d(x,x) = 0;
end
save result d;  
%sum(sum(d))
