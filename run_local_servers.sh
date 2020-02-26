#! /bin/bash

# Initialize variable defaults
start=false
rerun=false
sleep=false
stop=false 

# Check if in the correct directory
if [[ ! $PWD =~ (final-project-group-3)$ ]] ; then
  echo "In the wrong directory. Run in ExpoDB-BC. Exiting..."

  exit 1
fi

# Check if docker command exists
if ! hash docker 2> /dev/null; then
  echo "Docker command not found. Please install Docker"
  echo "Exiting..."

  exit 1
fi

# Check for existing/running processes (start,rerun,sleep,stop)
#pids=``

# Check for running Docker instance(start,rerun,sleep,stop)
containers=`docker ps -q`
if [[ ! -z "${containers}" ]] ; then
   if $start || $stop ; then
      echo "Cleaning up Docker containers..."

      (cd .. && docker-compose down)
   elif $sleep ; then
      echo "Night night. Zzzzzz..."

      exit 0
   fi
else
   echo "No Docker containers running"

   if $rerun ; then
      echo "Can't rerun without them. Exiting..."

      exit 1
   elif $sleep ; then
      echo "No need to sleep. Exiting..."

      exit 1
   fi
fi
