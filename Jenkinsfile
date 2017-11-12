#!/usr/bin/env groovy

node('master') {
   deleteDir()
   dir('swx_ci') {
      checkout([$class: 'GitSCM', 
              extensions: [[$class: 'CloneOption',  shallow: true]], 
              userRemoteConfigs: [[ url: 'https://github.com/MrBr-github/swx_ci.git']]
            ])
      }
  evaluate(readFile("${env.WORKSPACE}/swx_ci/_test_pipeline/tests.groovy"))
}
