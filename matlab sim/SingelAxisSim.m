l=10;
teta= 0;
X=[3;0];
x_des=0;
last_error = 0;
integral = 0;
dt = 0.05;
g=9.8;
kp=0.2;
kd=0.2;
ki=0;

i=0;


figure(1)

while(1)
   
    i=i+1;
    
xl=[-l/2*cos(teta);l/2*cos(teta)];
yl=[-l/2*sin(teta);l/2*sin(teta)];
cm=[X(1)*cos(teta);X(1)*sin(teta)];

plot(xl,yl,cm(1),cm(2),'r o')
axis([-10 10 -10 10])
grid on
drawnow
    
    error = X(1)-x_des;
    integral = integral + (error+last_error)*dt/2;
    div = (error-last_error)/dt;
    teta =kp*error+kd*div+ki*integral;
    last_error =error;
   
    if teta>20
        teta=20
    end
    if teta<-20
        teta=-20
    end
        
    
    
    
  
X = X +[X(2);-g*sin(teta)].*dt;
%X = X+0.05*[rand();rand()]

% K0 = [X(2);-g*sin(teta)]*dt/2;
% K1 = [X(2)+dt/2;-g*si(teta)
    
    
    
    

if abs(X(1))>10
    break
end

if and(i>150,i<300)
    x_des = 3;
end

if and(i>300,i<450)
    x_des = -4;
end

if i>450
    x_des = 0;
    i=0;
end



end