def tasks = [:]

tasks["task_1"] = {
  node('hpc-test-node') {
    stage ("SCM checkout"){    
      checkout scm
    }
    stage ("Building with GCC"){
      sh '''
        module load hpcx-gcc
        export SHMEM_HOME=$OMPI_HOME
        export CC=''
        cd verifier
        ./autogen.sh
        ./configure --prefix=$PWD/install
        make -j9
        make -j9 install
        module list ; # DEBUG
        hostname ;  # DEBUG
      '''
    }
    stage ("Run test with GCC"){
      sh '''
        module list ; # DEBUG
        hostname ;  # DEBUG
        module load hpcx-gcc
        verifier/install/bin/oshmem_test exec --no-colour --task=basic
      '''
    }
  }
}
tasks["task_2"] = {
  node('hpc-test-node2') {
    stage ("SCM checkout"){    
      checkout scm
    }
    stage ("Building with ICC"){
      sh '''
        module load intel/ics hpcx-icc
        export SHMEM_HOME=$OMPI_HOME
        export CC=''
        cd verifier
        ./autogen.sh
        ./configure --prefix=$PWD/install
        make -j9
        pwd; # DEBUG
        make -j9 install
        pwd; # DEBUG
        module list ; # DEBUG
        hostname ;  # DEBUG
      '''
    }
    stage ("Run test with ICC"){
      sh '''
        pwd; # DEBUG
        module list ; # DEBUG
        hostname ;  # DEBUG
        module load hpcx-icc
        cd $WORKSPACE
        verifier/install/bin/oshmem_test exec --no-colour --task=basic
      '''
    }
  }
}

parallel tasks
