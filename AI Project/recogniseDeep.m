%MOUYART Matthieu & PARDON Sarah Group F
function [c] = recogniseDeep(I,trainedNetwork)
% Recognise the student in image I from the 2021 Spring Y3 ING class
% Input : I (upright RGB image)
% Output : c (integer student id)

% your code ...

% example
I =imresize(I,[224 224]); % Resize the image to the format used by GoogleNet
[YPred] = classify(trainedNetwork,I); % Identify the person on the photo
c=string(YPred); % Store it into a variable c
c = strsplit(c,' '); % Extract the student id by splitting the string
c = str2double(c{1}); % Convert the student id into a double.

end