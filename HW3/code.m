load ('network_A') % load data
tree = zeros(100,100); %create a 100*100 matrix
x = length(A);         %determine the length of A
distance = zeros(100,100); %record the distance to the root node
node = zeros(100,100); %record node connects to each other

for n = 1:x            %record which node connects to root node
    if A(1,n) == 1       %if 1 means that node connects to root node
            distance(1,n) = 1;  %distance to root is 1 
            node(1,n) = 1;      %connect to root node representing 1
                for i = 1:x
                    if A(i,1) == 0        % this if to make sure that 0 is connectionless
                        distance(i,1) = 0; 
                        node(i,1) = 0;
                    end
                end
    end
end


D = sum(distance);    %define the initial value

for D = 1:x
    for i = 1:x
        if (distance(1,i) == D)                  
            for j = 1:x
                if A(i,j) == 1 && node(1,j) ==0  %find whether node doesn't be found
                    distance(1,j) = D+1;         %if found, then add 1 to distance
                    node(1,j) = i;               %then node will be update                   
                end
            end
        end
    end
end

for i = 1:x                      
    if distance(1,n) == i   %check whether the distance satisfies the demand     
        for n = 1:x      %this for-loop to create the tree
            tree(n,node(1,n))=1;
            tree(node(1,n),n)=1;
        end
    end
end

save result tree;  
    
sum(sum(tree))  %check my answer




