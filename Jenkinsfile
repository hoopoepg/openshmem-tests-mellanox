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
      '''
    }
    stage ("Run test with GCC"){
      sh "verifier/install/bin/oshmem_test exec --no-colour --task=basic"
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
        module load hpcx-icc
        export SHMEM_HOME=$OMPI_HOME
        export CC=''
        cd verifier
        ./autogen.sh
        ./configure --prefix=$PWD/install
        make -j9
        make -j9 install
      '''
    }
    stage ("Run test with ICC"){
      sh "verifier/install/bin/oshmem_test exec --no-colour --task=basic"
    }
  }
}

parallel tasks
