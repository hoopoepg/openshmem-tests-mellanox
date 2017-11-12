#!/usr/bin/env groovy
sh 'echo "======1=====";pwd; ls -la ' ; //DEBUG

node('master') {
  sh 'echo "======2=====";ls -la ' ; //DEBUG
  dir('swx_ci') {
    git url: 'https://github.com/MrBr-github/swx_ci.git'
  }
  sh 'echo "======3=====";ls -la ' ; //DEBUG
  evaluate(readFile("${env.WORKSPACE}/swx_ci/_test_pipeline/tests.groovy"))
}
