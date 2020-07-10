# use scientific linux base
FROM sl:7


# Label
LABEL maintainer="jgarra@slac.stanford.edu"
LABEL version="0.1"
LABEL description="Docker image containing software used in Eric Prebys' USPAS Accelerator Fundamentals online course in the summer of 2020."


COPY . /app

RUN yum -y update
RUN yum -y install man xorg-x11-apps libX* 
RUN chmod +x /app/madx
#source G4beamline-3.06/bin/g4bl-setup.sh

CMD bash /app/setup.sh