

%%Functions%%

function [bild] = rotationMatrice(rotDeg,urbild)
    radians = deg2rad(rotDeg);
    A = [cos(radians) -sin(radians) ; sin(radians) cos(radians)];
    bild = A*urbild;
end



%%Main code%%

x = [0 1 1 0 0];
y = [0 0 1 1 0];



xROT = [];
yROT = [];
frame = 0;
for (deg = 0:1:360)



    frame = frame + 1;

    for index = 1:1:length(x)

    kordPair = [x(index) , y(index)]';
    rotKORD = rotationMatrice(deg,kordPair);

    xROT(index) = rotKORD(1);
    yROT(index) = rotKORD(2);
    end
    
    
    plot(x,y,xROT,yROT)
    xlim([-2,2]);
    ylim([-2,2]);

    M(:,frame) = getframe;

end

movie(M,5,60)

