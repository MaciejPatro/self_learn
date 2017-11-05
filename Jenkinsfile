pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                sh 'scripts/prepare_build.sh uts testing=ON'
                sh 'cd ../build/uts && make -j4'
            }
        }
        stage('Running UTs') {
            steps {
                sh '../build/uts/exercises/ut/exercisesTests -r junit > ut_results.xml'
            }
        }
        stage('Sanitizers') {
            steps {
                parallel(
                    Address: {
                        sh 'scripts/prepare_build.sh asan asan=ON'
                  	    sh 'cd ../build/asan && make -j2'
                        sh '../build/asan/exercises/ut/exercisesTests'
                    },
                    Memory: {
                        sh 'scripts/prepare_build.sh msan msan=ON'
                  	    sh 'cd ../build/msan && make -j2'
                        sh 'echo "Solve problem with std library and Catch..."'
                    },
                     Threads: {
                        sh 'scripts/prepare_build.sh tsan tsan=ON'
                        sh 'cd ../build/tsan && make -j2'
                        sh '../build/tsan/exercises/ut/exercisesTests'
                     }
                )
		    }
        }
        stage('Build Product') {
            steps {
                sh 'scripts/prepare_build.sh deploy testing=OFF'
                sh 'cd ../build/deploy && make -j4'
            }
        }
    }
    post {
        always {
	        junit 'ut_results.xml'
	    }
    }
}