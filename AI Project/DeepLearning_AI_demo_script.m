%MOUYART Matthieu & PARDON Sarah Group F
% Only upload test images in directory
testFolder='C:\Users\user\Downloads\StudentsDemo\'; % Test directory
files=dir(testFolder); % Gather all images from the above directory

clear filenames         % Erase the previous results
for i=3:size(files,1)   % Files contains the root paths of folders, this loop allow to avoid them
    filenames{i-2,1}=files(i).name;
end

load 'DenseNet-201.mat';  % Load our network

wrongImages={}; w=1; % Initialize the matrix wrongImages(w,:) which contains the errors
correct=0; % Initialize the counter of correct answers
tic;    % Start measure of computation time
for i=1:size(filenames,1)
    I=imread(strcat(testFolder,(filenames{i}))); % Read the ith image in the folder
    c=recogniseDeep(I,trainedNetwork_1);  % Recognization of the image using a trained network
    sprintf("Student id: %i",c) % Printing the student id in the command window
    
    %Extracting the correct id from the filename
    correctId=strsplit(filenames{i},'-');
    correctId=str2double(correctId{1});
    
    if (c==correctId), 
        correct=correct+1; % If the guess is correct, increase this counter
    else
        wrongImages{w,1}=filenames{i}; % If the guess is wrong, gather the wrong guess and the corresponding image
        wrongImages{w,2}=c; 
        w=w+1; % Increase the mistakes counter
    end
    
    accuracy=100*(correct/i); % Evaluation of the current accuracy
    sprintf('Recognition rate = %f%% after %u images',accuracy,i);
    
end

sprintf('Average recognition time = %f seconds',toc/i) % Display of the average recognition time
wrongImages=wrongImages';    % Change the display of the 'mistake matrix' to one error per column